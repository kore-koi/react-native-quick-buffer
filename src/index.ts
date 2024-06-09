import {
  NativeQuickBufferModule as native,
  NativeQuickBuffer
} from "./NativeQuickBuffer"

class QuickBuffer {
  #internal: NativeQuickBuffer

  constructor(length: number) {
    this.#internal = native.createNativeQuickBuffer(length)

    return new Proxy(this, {
      get: (obj, key) => {

        if (typeof key === "string" && (Number.isInteger(Number(key)))) {
          console.log("HERE RETUN 0")
          return 0 // temp
        } else {

          console.log("HERE RETUN obj[key]", obj)
          return obj[key] // get a prop
        }

      },
      set: (obj, key, value) => {
        if (typeof key === "string" && (Number.isInteger(Number(key)))) {
          return 0 // temp
        } else {
          return obj[key] = value
        }
      }
    })
  }

  static alloc(length: number): QuickBuffer {
    return new QuickBuffer(length)
  }

  test = (): string => {

    return "test"
  }

}

export default QuickBuffer
