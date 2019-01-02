type t = [ | `Omit | `SameOrigin | `Include];

let encode =
  /* internal */
  fun
  | `Omit => "omit"
  | `SameOrigin => "same-origin"
  | `Include => "include";

let decode =
  /* internal */
  fun
  | "omit" => `Omit
  | "same-origin" => `SameOrigin
  | "include" => `Include
  | e => raise(Failure("Unknown requestCredentials: " ++ e));
