type t;

external makeWithObject: Js.t({..}) => t = "%identity";
external makeWithDict: Js.Dict.t(string) => t = "%identity";
external make: array((string, string)) => t = "%identity";
