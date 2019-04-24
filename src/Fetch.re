[@bs.val] external fetch: string => Js.Promise.t(Fetch_Response.t) = "fetch";

[@bs.val]
external fetchWithInit:
  (string, Fetch_RequestInit.t) => Js.Promise.t(Fetch_Response.t) =
  "fetch";

[@bs.val]
external fetchWithRequest: Fetch_Request.t => Js.Promise.t(Fetch_Response.t) =
  "fetch";

[@bs.val]
external fetchWithRequestInit:
  (Fetch_Request.t, Fetch_RequestInit.t) => Js.Promise.t(Fetch_Response.t) =
  "fetch";

module BodyInit = Fetch_BodyInit;
module Body = Fetch_Body;
module FormData = Fetch_FormData;
module Headers = Fetch_Headers;
module HeadersInit = Fetch_HeadersInit;
module ReadableStream = Fetch_ReadableStream;
module URLSearchParams = Fetch_URLSearchParams;
module XmlHttpRequest = Fetch_XmlHttpRequest;
module Response = Fetch_Response;
module ResponseInit = Fetch_ResponseInit;
module Request = Fetch_Request;
module RequestInit = Fetch_RequestInit;
module AbortController = Fetch_AbortController;
module AbortSignal = Fetch_AbortSignal;
