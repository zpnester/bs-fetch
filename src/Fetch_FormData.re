type t;


include Fetch_MapLike.Make({
  type nonrec t = t;
  type value =  [ | `String(string) | `Blob(FileReader.Blob.t)];
  let decodeValue = Fetch__.decodeEntryValue_;
});

[@bs.send]
external append:
  (
    t,
    string,
    [@bs.unwrap] [ | `String(string) | `Blob(FileReader.Blob.t)]
  ) =>
  unit =
  "append";

[@bs.send] external getAll_: (t, string) => array(Js.Json.t) = "getAll";
let getAll = (fd, name) =>
  fd->getAll_(name)->Belt.Array.map(Fetch__.decodeEntryValue_);

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

[@bs.new]
external make: (~form: Dom.htmlFormElement=?, unit) => t = "FormData";
