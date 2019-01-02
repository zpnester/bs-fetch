type t;

include (module type of Fetch_BodyLike.Make({
  type nonrec t = t;
}));
