import * as THREE from 'three';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader';

export class Model extends THREE.EventDispatcher {
    constructor(copy = null) {
        super();

        this.mesh = null;
        this.skeleton = null;
        this.mixer = null;
        this.action = null;
        this.gltf = null;
        this.animations = [];
        this.currentAnimation = 0;

        // Copy constructor, avoid loading n times the same model
        if (copy && typeof copy === "object" && copy.scene && copy.mesh) {
            this.makeClone(copy)
        }
    }

    makeClone({ scene, mesh }) {
        this.mesh = mesh.clone();

        scene.getScene().add(this.mesh);
    }

    async load(path, sceneWrapper, addToScene) {
        return new Promise((resolve, reject) => {
            new GLTFLoader().load(path, (gltf) => {
                this.gltf = gltf;
                this.mesh = this.gltf.scene;

                if (this.gltf.animations.length) {
                    // Skeleton
                    this.skeleton = new THREE.SkeletonHelper(this.mesh);
                    this.skeleton.visible = false;
                    sceneWrapper.getScene().add(this.skeleton);

                    // Animations handling
                    this.animations = this.gltf.animations;
                    this.mixer = new THREE.AnimationMixer(this.mesh);
                    this.action = this.mixer.clipAction(this.animations[this.currentAnimation]);
                    this.action.play();

                    sceneWrapper.addMixer(this.mixer);
                }

                if (addToScene)
                    sceneWrapper.getScene().add(this.mesh);
                resolve();
            }, undefined, reject)
        });
    }

    getMesh() {
        return this.mesh;
    }

    getGLTF() {
        return this.gltf;
    }

    getSize() {
        let size = new THREE.Vector3();
        let box = new THREE.Box3().setFromObject(this.mesh);
        box.getSize(size);

        return size;
    }

    getAnimationLength() {
        return this.animations.length;
    }

    playAnimationOnce(index) {
        if (index < 0 || index > this.getAnimationLength() - 1)
            return;

        this.action.stop();
        let action = this.mixer.clipAction(this.animations[index]);
        action.setLoop(THREE.LoopOnce);

        let callback = _ => {
            this.mixer.removeEventListener('finished', callback);
            action.stop();
            this.action.play();
            this.dispatchEvent({ type: 'animation-end' });
        };

        this.mixer.addEventListener('finished', callback);
        action.play();
    }

    setAnimationIndex(index) {
        if (index < 0 || index === this.currentAnimation || index > this.getAnimationLength() - 1)
            return;

        this.currentAnimation = index;
        this.action.stop();
        this.action = this.mixer.clipAction(this.animations[this.currentAnimation]);
        this.action.play();
    }
}