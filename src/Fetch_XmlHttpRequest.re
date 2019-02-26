type t;

/* XMLHttpRequestEventTarget */
[@bs.get] external loaded: Dom.progressEvent => float = "loaded";
[@bs.get] external total: Dom.progressEvent => float = "total";

[@bs.set]
external onprogress: (t, Dom.progressEvent => unit) => unit = "onprogress";
[@bs.set] external onloadstart: (t, unit => unit) => unit = "onloadstart";
[@bs.set] external onload: (t, Dom.progressEvent => unit) => unit = "onload";
[@bs.set] external onerror: (t, unit => unit) => unit = "onerror";
[@bs.set] external onabort: (t, unit => unit) => unit = "onabort";
/* end of XMLHttpRequestEventTarget */

[@bs.set]
external onreadystatechange: (t, unit => unit) => unit = "onreadystatechange";

type ready_state = [
  | `UNSENT
  | `OPENED
  | `HEADERS_RECEIVED
  | `LOADING
  | `DONE
];

[@bs.get] external readyState_: t => int = "readyState";
let readyState = (self): ready_state => {
  switch (readyState_(self)) {
  | 0 => `UNSENT
  | 1 => `OPENED
  | 2 => `HEADERS_RECEIVED
  | 3 => `LOADING
  | 4 => `DONE
  | _ => failwith("unxpected readyState")
  };
};

type response = [
  | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)
  | `Blob(FileReader.Blob.t)
  | `Document(Dom.document)
  | `Json(Js.Json.t)
  | `String(string)
];

let isDocument_: Js.Json.t => bool = [%raw
  {|
function(value) {
    return value instanceof Document;
}
|}
];

external asDocument__: Js.Json.t => Dom.document = "%identity";

let isArrayBuffer_: Js.Json.t => bool = [%raw
  {|
function(value) {
    return value instanceof ArrayBuffer;
}
|}
];

external asArrayBuffer__: Js.Json.t => Js.Typed_array.ArrayBuffer.t =
  "%identity";

let isBlob_: Js.Json.t => bool = [%raw
  {|
function(value) {
    return value instanceof Blob;
}
|}
];

external asBlob__: Js.Json.t => FileReader.Blob.t = "%identity";

[@bs.get] [@bs.return nullable]
external response_: t => option(Js.Json.t) = "response";


let response: t => option(response) = xhr => {
  switch (xhr->response_) {
  | Some(res) =>
    if (res->isDocument_) {
      Some(`Document(res->asDocument__));
    } else if (res->isBlob_) {
      Some(`Blob(res->asBlob__));
    } else if (res->isArrayBuffer_) {
      Some(`ArrayBuffer(res->asArrayBuffer__));
    } else {
      switch (res->Js.Json.decodeString) {
      | Some(string) => Some(`String(string))
      | None => Some(`Json(res))
      }
    }
  | None => None
  };
};

[@bs.get] [@bs.return nullable]
external responseText: t => option(string) = "responseText";

type response_type = [ | `text | `arraybuffer | `blob | `document | `json];

let toResponseType_ = (str): response_type => {
  switch (str) {
  | ""
  | "text" => `text
  | "arraybuffer" => `arraybuffer
  | "blob" => `blob
  | "document" => `document
  | "json" => `json
  | _ => failwith("unexpected response type")
  };
};

let fromResponseType_ = (rt: response_type): string => {
  switch (rt) {
  | `text => "text"
  | `arraybuffer => "arraybuffer"
  | `blob => "blob"
  | `document => "document"
  | `json => "json"
  };
};

[@bs.get] external responseType_: t => string = "responseType";
let responseType = xhr => xhr->responseType_->toResponseType_;

[@bs.set] external setResponseType_: (t, string) => unit = "responseType";
let setResponseType = (xhr, rt) =>
  xhr->setResponseType_(rt->fromResponseType_);

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

[@bs.send]
external open__:
  (t, string, string, bool, ~user: string=?, ~password: string=?, unit) => unit =
  "open";

let open_ =
    (
      xhr: t,
      method: Fetch_RequestMethod.t,
      url: string,
      ~async: option(bool)=?,
      ~user: option(string)=?,
      ~password: option(string)=?,
      (),
    ) => {
  /* async == true by default */
  let async =
    switch (async) {
    | Some(b) => b
    | None => true
    };
  xhr->open__(
    Fetch_RequestMethod.encode(method),
    url,
    async,
    ~user?,
    ~password?,
    (),
  );
};

[@bs.send] external overrideMimeType: (t, string) => unit = "overrideMimeType";

[@bs.send] external sendDocument: (t, Dom.document) => unit = "send";
[@bs.send] external sendBody: (t, Fetch_BodyInit.t) => unit = "send";
[@bs.send] external send: t => unit = "send";
[@bs.send]
external setRequestHeader: (t, string, string) => unit = "setRequestHeader";

[@bs.new] external make: unit => t = "XMLHttpRequest";
