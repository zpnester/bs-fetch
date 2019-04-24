

type t;


let make: unit => t;

[@bs.get] external signal: t => Fetch_AbortSignal.t = "signal";

[@bs.send] external abort: t => unit = "abort";
