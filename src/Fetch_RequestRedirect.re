type t = [ | `Follow | `Error | `Manual];

let encode =
  /* internal */
  fun
  | `Follow => "follow"
  | `Error => "error"
  | `Manual => "manual";

let decode =
  /* internal */
  fun
  | "follow" => `Follow
  | "error" => `Error
  | "manual" => `Manual
  | e => raise(Failure("Unknown requestRedirect: " ++ e));
