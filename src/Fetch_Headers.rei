type t;

include (module type of
  Fetch_MapLike.Make({
    type nonrec t = t;
    type value = string;
    external decodeValue: Js.Json.t => string = "%identity";
  }));

[@bs.send] external append: (t, string, string) => unit = "append";

[@bs.send] [@bs.return nullable]
external get: (t, string) => option(string) = "get";

[@bs.send] external set: (t, string, string) => unit = "set";

[@bs.send] external forEach: (t, string => unit) => unit = "forEach";

/* removed indirecton to HeadersInit, it is still used in RequestInit */

// constructors, avoid externals

let make: unit => t;
let makeWithObject: Js.t({..}) => t;
let makeWithDict: Js.Dict.t(string) => t;
let makeWithArray: array((string, string)) => t;
