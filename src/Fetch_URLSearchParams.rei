type t;

/* "This is an experimental technology" */

include (module type of
  Fetch_MapLike.Make({
    type nonrec t = t;
    type value = string;
    external decodeValue: Js.Json.t => string = "%identity";
  }));

[@bs.send] external append: (t, string, string) => unit = "append";

[@bs.send] external getAll: (t, string) => array(string) = "getAll";

[@bs.send] external set: (t, string, string) => unit = "set";

[@bs.send] external sort: t => unit = "sort";
[@bs.send] external toString: t => string = "toString";

// constructors, avoid extenral
let make: unit => t;
let makeWithString: string => t;
let makeWithObject: Js.t({..}) => t;
let makeWithDict: Js.Dict.t(string) => t;
let makeWithArray: array((string, string)) => t;
