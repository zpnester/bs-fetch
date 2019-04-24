type t;



let make: (
      ~method_: Fetch_RequestMethod.t=?,
      ~headers: Fetch_HeadersInit.t=?,
      ~body: Fetch_BodyInit.t=?,
      ~referrer: string=?,
      ~referrerPolicy: Fetch_ReferrerPolicy.t=?,
      ~mode: Fetch_RequestMode.t=?,
      ~credentials: Fetch_RequestCredentials.t=?,
      ~cache: Fetch_RequestCache.t=?,
      ~redirect: Fetch_RequestRedirect.t=?,
      ~integrity: string=?,
      ~keepalive: bool=?,
      ~signal: Fetch_AbortSignal.t=?,
      unit
    ) => t;