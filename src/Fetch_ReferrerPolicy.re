
type t = [
  | `None
  | `NoReferrer
  | `NoReferrerWhenDowngrade
  | `SameOrigin
  | `Origin
  | `StrictOrigin
  | `OriginWhenCrossOrigin
  | `StrictOriginWhenCrossOrigin
  | `UnsafeUrl
];

let encode =
  /* internal */
  fun
  | `None => ""
  | `NoReferrer => "no-referrer"
  | `NoReferrerWhenDowngrade => "no-referrer-when-downgrade"
  | `SameOrigin => "same-origin"
  | `Origin => "origin"
  | `StrictOrigin => "strict-origin"
  | `OriginWhenCrossOrigin => "origin-when-cross-origin"
  | `StrictOriginWhenCrossOrigin => "strict-origin-when-cross-origin"
  | `UnsafeUrl => "unsafe-url";

let decode =
  /* internal */
  fun
  | "" => `None
  | "no-referrer" => `NoReferrer
  | "no-referrer-when-downgrade" => `NoReferrerWhenDowngrade
  | "same-origin" => `SameOrigin
  | "origin" => `Origin
  | "strict-origin" => `StrictOrigin
  | "origin-when-cross-origin" => `OriginWhenCrossOrigin
  | "strict-origin-when-cross-origin" => `StrictOriginWhenCrossOrigin
  | "unsafe-url" => `UnsafeUrl
  | e => raise(Failure("Unknown referrerPolicy: " ++ e));