type t;

include (module type of
  Fetch_BodyLike.Make({
    type nonrec t = t;
  }));

[@bs.val] external error: unit => t = "error";

[@bs.val] external redirect: string => t = "redirect";

[@bs.val]
external redirectWithStatus: (string, int /* enum-ish */) => t = "redirect";

[@bs.get] external headers: t => Fetch_Headers.t = "headers";

[@bs.get] external ok: t => bool = "ok";

[@bs.get] external redirected: t => bool = "redirected";

[@bs.get] external status: t => int = "status";

[@bs.get] external statusText: t => string = "statusText";

[@bs.get] external type_: t => string = "type";

[@bs.get] external url: t => string = "url";

[@bs.send] external clone: t => unit = "clone";

// constructor, avoid extenral
let make:
  (~body: Fetch_BodyInit.t=?, ~init: Fetch_ResponseInit.t=?, unit) => t;
