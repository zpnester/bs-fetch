type t = [
  | `Default
  | `NoStore
  | `Reload
  | `NoCache
  | `ForceCache
  | `OnlyIfCached
];

let encode =
  /* internal */
  fun
  | `Default => "default"
  | `NoStore => "no-store"
  | `Reload => "reload"
  | `NoCache => "no-cache"
  | `ForceCache => "force-cache"
  | `OnlyIfCached => "only-if-cached";

let decode =
  /* internal */
  fun
  | "default" => `Default
  | "no-store" => `NoStore
  | "reload" => `Reload
  | "no-cache" => `NoCache
  | "force-cache" => `ForceCache
  | "only-if-cached" => `OnlyIfCached
  | e => raise(Failure("Unknown requestCache: " ++ e));
