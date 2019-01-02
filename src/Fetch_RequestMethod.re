type t =
  [ `Get
  | `Head
  | `Post
  | `Put
  | `Delete
  | `Connect
  | `Options
  | `Trace
  | `Patch
  | `Other(string) ];

let encode =
  /* internal */
  fun
  | `Get => "GET"
  | `Head => "HEAD"
  | `Post => "POST"
  | `Put => "PUT"
  | `Delete => "DELETE"
  | `Connect => "CONNECT"
  | `Options => "OPTIONS"
  | `Trace => "TRACE"
  | `Patch => "PATCH"
  | `Other(method) => method;

let decode =
  /* internal */
  fun
  | "GET" => `Get
  | "HEAD" => `Head
  | "POST" => `Post
  | "PUT" => `Put
  | "DELETE" => `Delete
  | "CONNECT" => `Connect
  | "OPTIONS" => `Options
  | "TRACE" => `Trace
  | "PATCH" => `Patch
  | method => `Other(method);