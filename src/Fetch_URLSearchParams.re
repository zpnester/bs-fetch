type t;

/* This is an experimental technology */

include Fetch_MapLike.Make({
  external decodeValue: Js.Json.t => string = "%identity";
  type nonrec t = t;
  type value = string;
  let decodeValue = decodeValue;
});

[@bs.send] external append: (t, string, string) => unit = "append";

[@bs.send] external getAll: (t, string) => array(string) = "getAll";

[@bs.send] external set: (t, string, string) => unit = "set";

[@bs.send] external sort: t => unit = "sort";
[@bs.send] external toString: t => string = "toString";

[@bs.new] external make: unit => t = "URLSearchParams";
[@bs.new] external makeWithString: string => t = "URLSearchParams";
[@bs.new] external makeWithObject: Js.t({..}) => t = "URLSearchParams";
[@bs.new] external makeWithDict: Js.Dict.t(string) => t = "URLSearchParams";
[@bs.new]
external makeWithArray: array((string, string)) => t = "URLSearchParams";
