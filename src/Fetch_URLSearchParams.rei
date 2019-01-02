type t;

/* This is an experimental technology */

/* include */
let delete: (t, string) => unit;
let entries: t => array((string, string));

let get: (t, string) => option(string);

let has: (t, string) => bool;

let keys: t => array(string);

let values: t => array(string);
/* end of include */

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
