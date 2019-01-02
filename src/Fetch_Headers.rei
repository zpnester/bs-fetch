type t;

/* include */
let delete: (t, string) => unit;
let entries: t => array((string, string));

let get: (t, string) => option(string);

let has: (t, string) => bool;

let keys: t => array(string);

let values: t => array(string);
/* end of include */

[@bs.send] external append: (t, string, string) => unit = "append";

[@bs.send] external set: (t, string, string) => unit = "set";

[@bs.send] external forEach: (t, string => unit) => unit = "forEach";

/* removed indirecton to HeadersInit, it is still used in RequestInit */

[@bs.new] external make: unit => t = "Headers";
[@bs.new] external makeWithObject: Js.t({..}) => t = "Headers";
[@bs.new] external makeWithDict: Js.Dict.t(string) => t = "Headers";
[@bs.new] external makeWithArray: array((string, string)) => t = "Headers";
