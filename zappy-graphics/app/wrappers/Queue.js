module.exports = class {
  constructor() {
    this.queue = [];
    this.offset = 0;
  }

  isEmpty() {
    return this.queue.length === 0;
  }

  enqueue(item) {
    this.queue.push(item);
  }

  dequeue() {
    if (this.queue.length === 0)
      return null;

    let item = this.queue[this.offset];

    if (++this.offset * 2 >= this.queue.length){
      this.queue = this.queue.slice(this.offset);
      this.offset = 0;
    }

    return item;
  }
};
