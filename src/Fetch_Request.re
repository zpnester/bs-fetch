type t;

open Fetch__;

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

include Fetch_BodyLike.Make({
  type nonrec t = t;
});

[@bs.new] external make: string => t = "Request";

[@bs.new]
external makeWithInit: (string, Fetch_RequestInit.t) => t = "Request";

[@bs.new] external makeWithRequest: t => t = "Request";
[@bs.new]
external makeWithRequestInit: (t, Fetch_RequestInit.t) => t = "Request";

[@bs.get] external method_: t => string = "method";

let method: t => Fetch_RequestMethod.t =
  self => Fetch_RequestMethod.decode(method_(self));

[@bs.get] external url: t => string = "url";

[@bs.get] external headers: t => Fetch_Headers.t = "headers";

[@bs.get] external type__: t => string = "type";

let type_: t => request_type = self => decodeRequestType(type__(self));

[@bs.get] external destination_: t => string = "destination";

let destination: t => request_destination =
  self => decodeRequestDestination(destination_(self));

[@bs.get] external referrer: t => string = "referrer";

[@bs.get] external referrerPolicy_: t => string = "referrerPolicy";

let referrerPolicy: t => Fetch_ReferrerPolicy.t =
  self => Fetch_ReferrerPolicy.decode(referrerPolicy_(self));

[@bs.get] external mode_: t => string = "mode";

let mode: t => Fetch_RequestMode.t =
  self => Fetch_RequestMode.decode(mode_(self));

[@bs.get] external credentials: t => string = "credentials";

let credentials: t => Fetch_RequestCredentials.t =
  self => Fetch_RequestCredentials.decode(credentials(self));

[@bs.get] external cache_: t => string = "cache";

let cache: t => Fetch_RequestCache.t =
  self => Fetch_RequestCache.decode(cache_(self));

[@bs.get] external redirect_: t => string = "redirect";

let redirect: t => Fetch_RequestRedirect.t =
  self => Fetch_RequestRedirect.decode(redirect_(self));

[@bs.get] external integrity: t => string = "integrity";

[@bs.get] external keepalive: t => bool = "keepalive";
