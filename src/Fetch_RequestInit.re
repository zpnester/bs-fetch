type t;

let map = f =>
  fun /* internal */
  | Some(v) => Some(f(v))
  | None => None;

[@bs.obj]
external make_:
  (
    ~_method: string=?,
    ~headers: Fetch_HeadersInit.t=?,
    ~body: Fetch_BodyInit.t=?,
    ~referrer: string=?,
    ~referrerPolicy: string=?,
    ~mode: string=?,
    ~credentials: string=?,
    ~cache: string=?,
    ~redirect: string=?,
    ~integrity: string=?,
    ~keepalive: bool=?,
    ~signal: Fetch_AbortSignal.t=?,
    unit
  ) =>
  t =
  "";

let make =
    (
      ~method_: option(Fetch_RequestMethod.t)=?,
      ~headers: option(Fetch_HeadersInit.t)=?,
      ~body: option(Fetch_BodyInit.t)=?,
      ~referrer: option(string)=?,
      ~referrerPolicy: Fetch_ReferrerPolicy.t=`None,
      ~mode: option(Fetch_RequestMode.t)=?,
      ~credentials: option(Fetch_RequestCredentials.t)=?,
      ~cache: option(Fetch_RequestCache.t)=?,
      ~redirect: option(Fetch_RequestRedirect.t)=?,
      ~integrity: string="",
      ~keepalive: option(bool)=?,
      ~signal=?,
    ) =>
  make_(
    ~_method=?map(Fetch_RequestMethod.encode, method_),
    ~headers?,
    ~body?,
    ~referrer?,
    ~referrerPolicy=Fetch_ReferrerPolicy.encode(referrerPolicy),
    ~mode=?map(Fetch_RequestMode.encode, mode),
    ~credentials=?map(Fetch_RequestCredentials.encode, credentials),
    ~cache=?map(Fetch_RequestCache.encode, cache),
    ~redirect=?map(Fetch_RequestRedirect.encode, redirect),
    ~integrity,
    ~keepalive?,
    ~signal?
  );
