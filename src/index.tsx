const QuickBuffer = require('./NativeQuickBuffer').default;

export function multiply(a: number, b: number): number {
  return QuickBuffer.multiply(a, b);
}
