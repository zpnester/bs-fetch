type t;

include (module type of
  Fetch_MapLike.Make({
    type nonrec t = t;
    type value = [ | `String(string) | `Blob(FileReader.Blob.t)];
    let decodeValue = Fetch__.decodeEntryValue_;
  }));

[@bs.send]
external append:
  (
    t,
    string,
    [@bs.unwrap] [ | `String(string) | `Blob(FileReader.Blob.t)]
  ) =>
  unit =
  "append";

let getAll:
  (t, string) => array([ | `String(string) | `Blob(FileReader.Blob.t)]);

[@bs.send]
external set:
  (
    t,
    string,
    [@bs.unwrap] [ | `String(string) | `Blob(FileReader.Blob.t)],
    ~filename: string=?,
    unit
  ) =>
  unit =
  "set";

// constructor, avoid externals
let make: (~form: Dom.htmlFormElement=?, unit) => t;
