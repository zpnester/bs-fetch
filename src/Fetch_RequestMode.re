type t = [ | `Navigate | `SameOrigin | `NoCORS | `CORS];

let encode =
  /* internal */
  fun
  | `Navigate => "navigate"
  | `SameOrigin => "same-origin"
  | `NoCORS => "no-cors"
  | `CORS => "cors";

let decode =
  /* internal */
  fun
  | "navigate" => `Navigate
  | "same-origin" => `SameOrigin
  | "no-cors" => `NoCORS
  | "cors" => `CORS
  | e => raise(Failure("Unknown requestMode: " ++ e));
