type t;


type request_destination = [
  | `None 
  | `Document 
  | `Embed 
  | `Font 
  | `Image 
  | `Manifest 
  | `Media 
  | `Object 
  | `Report 
  | `Script 
  | `ServiceWorker 
  | `SharedWorker 
  | `Style 
  | `Worker 
  | `Xslt 
];

type request_type = [
  | `None 
  | `Audio 
  | `Font 
  | `Image 
  | `Script 
  | `Style 
  | `Track 
  | `Video 
];


include (module type of Fetch_BodyLike.Make({
  type nonrec t = t;
}));

// constructors, avoid externals
let make: string => t;

let makeWithInit: (string, Fetch_RequestInit.t) => t;
let makeWithRequest: t => t;
let makeWithRequestInit: (t, Fetch_RequestInit.t) => t;


let method: t => Fetch_RequestMethod.t;
[@bs.get] external url: t => string = "url";
[@bs.get] external headers: t => Fetch_Headers.t = "headers";
let type_: t => request_type;

let destination: t => request_destination;


[@bs.get] external referrer: t => string = "referrer";
let referrerPolicy: t => Fetch_ReferrerPolicy.t;

let mode: t => Fetch_RequestMode.t;

let credentials: t => Fetch_RequestCredentials.t;

let cache: t => Fetch_RequestCache.t;

let redirect: t => Fetch_RequestRedirect.t;


[@bs.get] external integrity: t => string = "integrity";

[@bs.get] external keepalive: t => bool = "keepalive";

