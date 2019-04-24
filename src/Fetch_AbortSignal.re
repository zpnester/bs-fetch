

type t;

[@bs.get] external aborted: t => bool = "aborted";

[@bs.set] external setOnAbort: (t, unit => unit) => unit = "onabort";