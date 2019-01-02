type t;

/* FormDataEntryValue */
type entry_value = [ | `String(string) | `Blob(FileReader.Blob.t)];

external asBlob_: Js.Json.t => FileReader.Blob.t = "%identity";


let isBlob_: Js.Json.t => bool = [%raw
  {|
function(value) {
  return value instanceof Blob;
}
|}
];

let decodeEntryValue_: Js.Json.t => entry_value =
  json =>
    if (json->isBlob_) {
      `Blob(json->asBlob_);
    } else {
      switch (json->Js.Json.decodeString) {
      | Some(string) => `String(string)
      | None => failwith("unexpected entry value")
      };
    };

include Fetch_MapLike.Make({
  type nonrec t = t;
  type value = entry_value;
  let decodeValue = decodeEntryValue_;
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
  fd->getAll_(name)->Belt.Array.map(decodeEntryValue_);

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
