type t;

include (module type of
  Fetch_BodyLike.Make({
    type nonrec t = t;
  }));

let error: unit => t;
let redirect: string => t;
let redirectWithStatus: (string, int /* enum-ish */) => t;
let headers: t => Fetch_Headers.t;
let ok: t => bool;
let redirected: t => bool;
let status: t => int;
let statusText: t => string;
let type_: t => string;
let url: t => string;
let clone: t => unit;

[@bs.new]
external make:
  (~body: Fetch_BodyInit.t=?, ~init: Fetch_ResponseInit.t=?, unit) => t =
  "Response";
