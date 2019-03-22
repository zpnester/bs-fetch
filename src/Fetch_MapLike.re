module Make =
       (
         M: {
           type t;
           type value;

           let decodeValue: Js.Json.t => value;
         },
       ) => {
  /* append  is unique for FormData */

  [@bs.send] external delete: (M.t, string) => unit = "delete";

  [@bs.send]
  external entries_: M.t => Js.Array.array_like((string, Js.Json.t)) =
    "entries";
  let entries: M.t => array((string, M.value)) =
    self =>
      self
      ->entries_
      ->Js.Array.from
      ->Belt.Array.map(((name, value)) => (name, value->M.decodeValue));

  [@bs.send] [@bs.return nullable]
  external get_: (M.t, string) => option(Js.Json.t) = "get";
  let get: (M.t, string) => option(M.value) =
    (self, name) => self->get_(name)->Belt.Option.map(M.decodeValue);

  /* getAll obsolete in Headers */

  [@bs.send] external has: (M.t, string) => bool = "has";

  [@bs.send] external keys_: M.t => Js.Array.array_like(string) = "keys";
  let keys = self => self->keys_->Js.Array.from;

  /* set is unique for FormData */

  [@bs.send]
  external values_: M.t => Js.Array.array_like(Js.Json.t) = "values";
  let values = self =>
    self->values_->Js.Array.from->Belt.Array.map(M.decodeValue);
};
