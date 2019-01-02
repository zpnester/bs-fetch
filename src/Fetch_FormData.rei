type t;

type entry_value = [ | `String(string) | `Blob(FileReader.Blob.t)];

/* include */

let delete: (t, string) => unit;
let entries: t => array((string, entry_value));

let get: (t, string) => option(entry_value);

let has: (t, string) => bool;

let keys: t => array(string);

let values: t => array(entry_value);
/* end of include */

let append:
  (t, string, [ | `String(string) | `Blob(FileReader.Blob.t)]) => unit;

let getAll: (t, string) => array(entry_value);

let set:
  (
    t,
    string,
    [ | `String(string) | `Blob(FileReader.Blob.t)],
    ~filename: string=?,
    unit
  ) =>
  unit;

let make: (~form: Dom.htmlFormElement=?, unit) => t;
