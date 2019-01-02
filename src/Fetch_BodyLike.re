module Make = (T: {type t;}) => {
  [@bs.get] external body: T.t => Fetch_ReadableStream.t = "body";

  [@bs.get] external bodyUsed: T.t => bool = "bodyUsed";

  [@bs.send]
  external arrayBuffer: T.t => Js.Promise.t(Js.Typed_array.ArrayBuffer.t) =
    "arrayBuffer";

  [@bs.send] external blob: T.t => Js.Promise.t(FileReader.Blob.t) = "blob";

  [@bs.send]
  external formData: T.t => Js.Promise.t(Fetch_FormData.t) = "formData";

  [@bs.send] external json: T.t => Js.Promise.t(Js.Json.t) = "json";

  [@bs.send] external text: T.t => Js.Promise.t(string) = "text";
};
