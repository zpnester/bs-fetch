type t;

let make:
  (~status: int=?, ~statusText: string=?, ~headers: Fetch_Headers.t=?, unit) =>
  t;
