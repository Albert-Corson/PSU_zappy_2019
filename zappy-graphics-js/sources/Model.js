export class Model {
    constructor() {
        this.geometry = new THREE.BoxGeometry();
        this.material = new THREE.MeshBasicMaterial({ color: 0x00ff00 });
        this.mesh = new THREE.Mesh(this.geometry, this.material);
    }

    getMesh() {
        return this.mesh;
    }
}