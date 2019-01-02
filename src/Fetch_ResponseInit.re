 type t;

  [@bs.obj] external make: (
    ~status: int=?, 
    ~statusText: string=?,
    ~headers: Fetch_Headers.t=?,
    unit
  ) => t = "";