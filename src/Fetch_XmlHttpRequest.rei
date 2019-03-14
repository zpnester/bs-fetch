type t;

[@bs.get] external loaded: Dom.progressEvent => float = "loaded";
[@bs.get] external total: Dom.progressEvent => float = "total";

[@bs.set]
external onprogress: (t, Dom.progressEvent => unit) => unit = "onprogress";
[@bs.set] external onloadstart: (t, unit => unit) => unit = "onloadstart";
[@bs.set] external onload: (t, Dom.progressEvent => unit) => unit = "onload";
[@bs.set] external onerror: (t, unit => unit) => unit = "onerror";
[@bs.set] external onabort: (t, unit => unit) => unit = "onabort";

[@bs.set]
external onreadystatechange: (t, unit => unit) => unit = "onreadystatechange";

let readyState:
  t => [ | `UNSENT | `OPENED | `HEADERS_RECEIVED | `LOADING | `DONE];

let response:
  t =>
  option(
    [
      | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)
      | `Blob(FileReader.Blob.t)
      | `Document(Dom.document)
      | `Json(Js.Json.t)
      | `String(string)
    ],
  );

[@bs.get] [@bs.return nullable]
external responseText: t => option(string) = "responseText";

let responseType: t => [ | `text | `arraybuffer | `blob | `document | `json];
let setResponseType:
  (t, [ | `text | `arraybuffer | `blob | `document | `json]) => unit;

[@bs.get] external responseURL: t => string = "responseURL";

[@bs.get] [@bs.return nullable]
external responseXML: t => option(Dom.document) = "responseXML";

[@bs.get] external status: t => int = "status";

[@bs.get] external statusText: t => string = "statusText";

[@bs.get] external timeout: t => float = "timeout";

[@bs.set] external setTimeout: (t, float) => unit = "timeout";

[@bs.set] external ontimeout: (t, unit => unit) => unit = "ontimeout";

/* upload */

[@bs.get] external withCredentials: t => bool = "withCredentials";
[@bs.set] external setWithCredentials: (t, bool) => unit = "withCredentials";

[@bs.send] external abort: t => unit = "abort";

[@bs.send] [@bs.return nullable]
external getAllResponseHeaders: t => option(string) = "getAllResponseHeaders";

[@bs.send] [@bs.return nullable]
external getResponseHeader: (t, string) => option(string) =
  "getResponseHeader";

let open_:
  (
    t,
    Fetch_RequestMethod.t,
    string,
    ~async: bool=?,
    ~user: string=?,
    ~password: string=?,
    unit
  ) =>
  unit;

[@bs.send] external overrideMimeType: (t, string) => unit = "overrideMimeType";

[@bs.send] external sendDocument: (t, Dom.document) => unit = "send";
[@bs.send] external sendBody: (t, Fetch_BodyInit.t) => unit = "send";
[@bs.send] external send: t => unit = "send";
[@bs.send]
external setRequestHeader: (t, string, string) => unit = "setRequestHeader";

// constructor, avoid external
let make: unit => t;
