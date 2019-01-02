type t;

external make: string => t = "%identity";
external makeWithBlob: FileReader.Blob.t => t = "%identity";
external makeWithArrayBuffer: Js.Typed_array.ArrayBuffer.t => t = "%identity";
external makeWithInt8Array: Js.Typed_array.Int8Array.t => t = "%identity";
external makeWithUint8Array: Js.Typed_array.Uint8Array.t => t = "%identity";
external makeWithUint8ClampedArray: Js.Typed_array.Uint8ClampedArray.t => t =
  "%identity";
external makeWithInt16Array: Js.Typed_array.Int16Array.t => t = "%identity";
external makeWithUint16Array: Js.Typed_array.Uint16Array.t => t = "%identity";
external makeWithInt32Array: Js.Typed_array.Int32Array.t => t = "%identity";
external makeWithUint32Array: Js.Typed_array.Uint32Array.t => t = "%identity";
external makeWithFloat32Array: Js.Typed_array.Float32Array.t => t =
  "%identity";
external makeWithFloat64Array: Js.Typed_array.Float64Array.t => t =
  "%identity";
external makeWithDataView: Js.Typed_array.DataView.t => t = "%identity";

external makeWithFormData: Fetch_FormData.t => t = "%identity";
external makeWithUrlSearchParams: Fetch_URLSearchParams.t => t = "%identity";
external makeWithReadableStream: Fetch_ReadableStream.t => t = "%identity";
