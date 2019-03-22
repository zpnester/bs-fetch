module Make:
  (
    M: {
      type t;
      type value;

      let decodeValue: Js.Json.t => value;
    },
  ) =>
   {
    [@bs.send] external delete: (M.t, string) => unit = "delete";

    let entries: M.t => array((string, M.value));

    let get: (M.t, string) => option(M.value);

    [@bs.send] external has: (M.t, string) => bool = "has";

    let keys: M.t => array(string);

    let values: M.t => array(M.value);
  };
