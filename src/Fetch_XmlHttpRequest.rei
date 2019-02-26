type t;

let loaded: Dom.progressEvent => float;
let total: Dom.progressEvent => float;

let onprogress: (t, Dom.progressEvent => unit) => unit;
let onloadstart: (t, unit => unit) => unit;
let onload: (t, Dom.progressEvent => unit) => unit;
let onerror: (t, unit => unit) => unit;
let onabort: (t, unit => unit) => unit;

let onreadystatechange: (t, unit => unit) => unit;

type ready_state = [
  | `UNSENT
  | `OPENED
  | `HEADERS_RECEIVED
  | `LOADING
  | `DONE
];

let readyState: t => ready_state;

type response = [
  | `ArrayBuffer(Js.Typed_array.ArrayBuffer.t)
  | `Blob(FileReader.Blob.t)
  | `Document(Dom.document)
  | `Json(Js.Json.t)
  | `String(string)
];

let response: t => option(response);

let responseText: t => option(string);

type response_type = [ | `text | `arraybuffer | `blob | `document | `json];

let responseType: t => response_type;
let setResponseType: (t, response_type) => unit;

let responseURL: t => string;

let responseXML: t => option(Dom.document);

let status: t => int;
let statusText: t => string;
let timeout: t => float;
let setTimeout: (t, float) => unit;

let ontimeout: (t, unit => unit) => unit;

/* upload */

let withCredentials: t => bool;
let setWithCredentials: (t, bool) => unit;

let abort: t => unit;
let getAllResponseHeaders: t => option(string);

let getResponseHeader: (t, string) => option(string);

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

let overrideMimeType: (t, string) => unit;

let sendDocument: (t, Dom.document) => unit;
let sendBody: (t, Fetch_BodyInit.t) => unit;
let send: t => unit;
let setRequestHeader: (t, string, string) => unit;

let make: unit => t;
