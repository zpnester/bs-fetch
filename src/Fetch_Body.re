type t;

include Fetch_BodyLike.Make({
  type nonrec t = t;
});
