
let decodeRequestDestination =
  /* internal */
  fun
  | "" => `None
  | "document" => `Document
  | "embed" => `Embed
  | "font" => `Font
  | "image" => `Image
  | "manifest" => `Manifest
  | "media" => `Media
  | "object" => `Object
  | "report" => `Report
  | "script" => `Script
  | "serviceworker" => `ServiceWorker
  | "sharedworder" => `SharedWorker
  | "style" => `Style
  | "worker" => `Worker
  | "xslt" => `Xslt
  | e => raise(Failure("Unknown requestDestination: " ++ e));



let decodeRequestType =
  /* internal */
  fun
  | "" => `None
  | "audio" => `Audio
  | "font" => `Font
  | "image" => `Image
  | "script" => `Script
  | "style" => `Style
  | "track" => `Track
  | "video" => `Video
  | e => raise(Failure("Unknown requestType: " ++ e));


/* FormData */
external asBlob_: Js.Json.t => FileReader.Blob.t = "%identity";


let isBlob_: Js.Json.t => bool = [%raw
  {|
function(value) {
  return value instanceof Blob;
}
|}
];


let decodeEntryValue_: Js.Json.t =>  [ | `String(string) | `Blob(FileReader.Blob.t)] =
  json =>
    if (json->isBlob_) {
      `Blob(json->asBlob_);
    } else {
      switch (json->Js.Json.decodeString) {
      | Some(string) => `String(string)
      | None => failwith("unexpected entry value")
      };
    };