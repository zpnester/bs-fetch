type t;

/* "This is an experimental technology" */

include (module type of Fetch_MapLike.Make({
  type nonrec t = t;
  type value = string;
  external decodeValue: Js.Json.t => string = "%identity";
}));


let append: (t, string, string) => unit;

let getAll: (t, string) => array(string);

let set: (t, string, string) => unit;

let sort: t => unit;
let toString: t => string;

let make: unit => t;
let makeWithString: string => t;
let makeWithObject: Js.t({..}) => t;
let makeWithDict: Js.Dict.t(string) => t;
let makeWithArray: array((string, string)) => t;
