type t;


include (module type of Fetch_MapLike.Make({
  type nonrec t = t;
  type value = [ | `String(string) | `Blob(FileReader.Blob.t)];
  let decodeValue = Fetch__.decodeEntryValue_;
}));



let append:
  (t, string, [ | `String(string) | `Blob(FileReader.Blob.t)]) => unit;

let getAll: (t, string) => array([ | `String(string) | `Blob(FileReader.Blob.t)]);

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
