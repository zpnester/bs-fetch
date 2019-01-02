
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