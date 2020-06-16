const Manager = class {

	/**
	 * @type {boolean}
	 * @private
	 */
	static _isInitialized = false;

	/**
	 * Contains sounds names array (key => reference id, value => array of names)
	 * @type {object}
	 * @private
	 */
	static _groups = {};

	/**
	 * Contains indexes arrays (key => reference id, value => the indexes array)
	 * @type {object}
	 * @private
	 */
	static _indexes = {};

	static _muted = false;

	static _ensureIsInitialized() {
		if (this._isInitialized) {
			return;
		}
		createjs.Sound.registerPlugins([createjs.WebAudioPlugin]);
		this._startAudioContext();
		this._isInitialized = true;
	}

	/**
	 * Audio plugin must be resume on user event
	 * @private
	 */
	static _startAudioContext() {
		const handler = () => {
			if (createjs.WebAudioPlugin.context && createjs.WebAudioPlugin.context.state === "suspended") {
				createjs.WebAudioPlugin.context.resume()
					.then(_ => {
						window.removeEventListener('click', handler);
						window.dispatchEvent(new CustomEvent('audio-plugin-resumed'))
					})
					.catch(e => {
						console.error("There was an error while trying to resume the SoundJS Web Audio context");
						console.error(e);
					});
			}
		};
		window.addEventListener("click", handler);
	}

	/**
	 * Return file name
	 * @param path
	 * @returns {string}
	 * @private
	 */
	static _getFileName(path) {
		const file = path.split('/');
		return file[file.length - 1].split('.')[0];
	}

	/**
	 * Check if id is already assigned or not
	 * @param {string|number} id
	 * @returns {boolean}
	 * @private
	 */
	static _hasGroup(id) {
		return !!Object.keys(this._groups).filter(k => k === id).length;
	}

	/**
	 * Register a SoundRef with corresponding id and options
	 * @param {string|number} id
	 * @param {SoundRef} ref
	 * @return boolean
	 * */
	static register(id, ref) {

		this._ensureIsInitialized();

		let files;

		if (!ref || !id) {
			return false;
		}

		if (this._hasGroup(id)) {
			console.error(`${id}: Reference id must be unique`);
			return false;
		}

		createjs.Sound.on('fileerror', (e) => {
			let idx;

			console.error(`Error while loading ${e.src}, verify that the file exists`);
			if (Array.isArray(files) && files.length && (idx = files.indexOf(e.id)) !== -1) {
				files.splice(idx, 1);
			}
		});

		const pathPrefix = 'sounds/';

		if (typeof ref.source === 'string') {
			const name = this._getFileName(ref.source);

			createjs.Sound.registerSound(pathPrefix + ref.source, name);

			files = [name];
		} else if (Array.isArray(ref.source)) {
			files = ref.source.map(path => {
				const name = this._getFileName(path);

				createjs.Sound.registerSound(pathPrefix + path, name);
				return name;
			});
		}

		if (files) {
			this._groups[id] = {
				files,
				loop: ref.loop,
				random: ref.random,
				streamsLimit: ref.streamsLimit,
				volume: ref.volume,
				fadeIn: ref.fadeIn,
				stream: []
			};
			return true;
		}

		return false;
	}

	/**
	 * Play reference sounds according to the object options
	 * @param {string|number} id
	 * @return boolean
	 */
	static play(id) {
		if (!this._hasGroup(id)) {
			console.error(`Requested reference ${id} does not exists`);
			return false;
		}

		const group = this._groups[id];
		let audioInstance, i;

		if (group.stream.length >= group.streamsLimit && !group.loop) {
			return false;
		}

		if (group.stream.filter(instance => instance.paused === true).length) {
			group.stream.map(instance => instance.paused = false);
			return false;
		}

		if (!this._indexes[id] || !this._indexes[id].length) {
			this._indexes[id] = Array(group.files.length).fill(0).map((a, i) => i)
		}

		if (group.isLooping) {
			console.log(`Reference ${id} is already playing`);
			return false;
		}

		if (!group.random && !group.procedural) {
			i = 0;
		} else if (!group.random && group.procedural) {
			i = Math.floor(Math.random() * this._indexes[id].length);
		} else if (group.random && !group.procedural) {
			i = Math.floor(Math.random() * group.files.length);
		} else {
			console.error('Random and procedural are not compatible options');
			return false;
		}

		let fileIndex = this._indexes[id][i];
		if (!group.files[fileIndex]) {
			console.error(`File not available`);
			return false;
		}
		group.stream.push(audioInstance = createjs.Sound.play(group.files[fileIndex]));
		audioInstance.volume = group.volume;

		if(group.fadeIn){
			if(group.loop) group.fadeIn = false;

			audioInstance.volume = 0;
			audioInstance.tween = createjs.Tween.get(audioInstance).to({
				volume: group.volume
			}, 1000, createjs.Ease.quintIn);
		}

		if (!group.random) {
			this._indexes[id].splice(i, 1);
		}

		if (group.loop) {
			group.isLooping = true;
			audioInstance.on('complete', _ => {
				group.isLooping = false;
				this.play(id);
			}, this, true);
		} else {
			audioInstance.on('complete', e => {
				group.stream.splice(group.stream.indexOf(e.target), 1);
			}, this, true);
		}

		return true;
	}

	/**
	 * @param {string|number} id
	 * @return boolean
	 */
	static pause(id) {
		if (!this._hasGroup(id)) {
			console.error('Requested reference does not exists');
			return false;
		}

		const instances = this._groups[id].stream;
		instances.map(instance => instance.paused = true);

		return true;
	}

	/**
	 * @param {string|number} id
	 * @return boolean
	 */
	static stop(id) {
		if (!this._hasGroup(id)) {
			console.error('Requested reference does not exists');
			return false;
		}

		if (this._groups[id].loop) {
			this._groups[id].isLooping = false;
		}
		const instances = this._groups[id].stream;
		instances.map(instance => instance.stop());

		return true;
	}

	static stopAll() {
		Object.keys(this._groups).map(k => this.stop(k));
	}

	static get muted() {
		return this._muted
	}

	static set muted(b) {
		this._muted = b
		createjs.Sound.muted = b
	}

	/**
	 * @param id
	 * @return {boolean}
	 */
	static unregister(id) {
		if (this._hasGroup(id)) {
			delete this._groups[id];
			return true;
		}
		return false;
	}

	static unregisterAll() {
		let groupNames = Object.keys(this._groups);
		groupNames.forEach(groupName => this.unregister(groupName));
	}
};

const SoundRef = class {
	constructor(source, options = {}) {
		this._source = source;
		this._loop = options.loop || false;
		this._random = options.random || false;
		this._procedural = options.procedural || false;
		this._streamsLimit = options.streamsLimit || 1;
		this._volume = options.volume || 1;
		this._fadeIn = options.fadeIn || false;
	}

	get source() {
		return this._source;
	}

	get loop() {
		return this._loop;
	}

	get random() {
		return this._random;
	}

	get procedural() {
		return this._procedural;
	}

	get streamsLimit() {
		return this._streamsLimit;
	}

	get volume() {
		return this._volume;
	}

	get fadeIn() {
		return this._fadeIn;
	}

	get volume() {
		return this._volume;
	}

	get fadeIn() {
		return this._fadeIn;
	}
};

export { Manager, SoundRef }
