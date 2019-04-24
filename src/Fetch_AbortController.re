

type t;


[@bs.new] external make: unit => t = "AbortController";

[@bs.get] external signal: t => Fetch_AbortSignal.t = "signal";

[@bs.send] external abort: t => unit = "abort";
