type t;

/* safe */
external decodeValue: Js.Json.t => string = "%identity";

include Fetch_MapLike.Make({
  type nonrec t = t;
  type value = string;
  let decodeValue = decodeValue;
});

[@bs.send] external append: (t, string, string) => unit = "append";

[@bs.send] external set: (t, string, string) => unit = "set";

[@bs.send] [@bs.return nullable]
external get: (t, string) => option(string) = "get";


[@bs.send] external forEach: (t, string => unit) => unit = "forEach";

/* removed indirecton to HeadersInit, it is still used in RequestInit */

[@bs.new] external make: unit => t = "Headers";
[@bs.new] external makeWithObject: Js.t({..}) => t = "Headers";
[@bs.new] external makeWithDict: Js.Dict.t(string) => t = "Headers";
[@bs.new] external makeWithArray: array((string, string)) => t = "Headers";
