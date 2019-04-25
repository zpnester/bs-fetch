open Js.Promise;
open Fetch;
open Expect;
open FileReader;
open Belt;

module FormData = Fetch_FormData;

let isEdge: bool = [%raw {|
(navigator.appVersion.indexOf("Edge") != -1)
|}];

// FORM DATA
let fd = FormData.make();
expectToEqual(fd->FormData.entries, [||]);
if (!isEdge) {
  expectToEqual(fd->FormData.getAll("name1"), [||]);
};
expectToEqual(fd->FormData.get("name1"), None);
expectToEqual(fd->FormData.keys, [||]);

let blob1 = Blob.make([|`String("value11")|], ());

fd->FormData.append("name1", `String("value1"));
expectToEqual(fd->FormData.get("name1"), Some(`String("value1")));

fd->FormData.append("name2", `String("value2"));
fd->FormData.append("name1", `Blob(blob1));

expectToEqual(fd->FormData.entries->Js.Array.length, 3);
expectToEqual(
  fd->FormData.entries->Belt.Array.getExn(0),
  ("name1", `String("value1")),
);
expectToEqual(
  fd->FormData.entries->Belt.Array.getExn(1),
  ("name2", `String("value2")),
);
switch (fd->FormData.entries->Belt_Array.getExn(2)) {
| ("name1", `Blob(value)) => expectInstanceOf(value, blob_ctor)
| _ => failwith("fail")
};

if (!isEdge) {
  expectToEqual(fd->FormData.getAll("name1")->Array.length, 2);
};

fd->FormData.set(
  "name1",
  `Blob(Blob.make([||], ())),
  ~filename="newfile",
  (),
);

if (!isEdge) {
  expectToEqual(fd->FormData.getAll("name1")->Array.length, 1);
};

switch (fd->FormData.get("name1")) {
| Some(`Blob(_)) => ()
| _ => failwith("fail")
};

expectToEqual(fd->FormData.get("name2"), Some(`String("value2")));
fd->FormData.delete("name2");
expectToEqual(fd->FormData.get("name2"), None);

// edge returns 2 name1
if (!isEdge) {
  expectToEqual(fd->FormData.keys, [|"name1"|]);
};

expectToEqual(fd->FormData.has("name1"), true);
expectToEqual(fd->FormData.has("name5"), false);

module URLSearchParams = Fetch.URLSearchParams;

// URL SEARCH PARAMS

let usp =
  URLSearchParams.makeWithArray([|
    ("1", "first"),
    ("2", "second"),
    ("1", "uno"),
  |]);

expectToEqual(
  usp->URLSearchParams.entries,
  [|("1", "first"), ("2", "second"), ("1", "uno")|],
);

expectToEqual(usp->URLSearchParams.values, [|"first", "second", "uno"|]);
usp->URLSearchParams.sort;
expectToEqual(usp->URLSearchParams.values, [|"first", "uno", "second"|]);

expectToEqual(usp->URLSearchParams.toString, "1=first&1=uno&2=second");
expectToEqual(usp->URLSearchParams.keys, [|"1", "1", "2"|]);
expectToEqual(usp->URLSearchParams.get("1"), Some("first"));
expectToEqual(usp->URLSearchParams.get("5"), None);

expectToEqual(usp->URLSearchParams.has("1"), true);
expectToEqual(usp->URLSearchParams.has("5"), false);

usp->URLSearchParams.delete("1");
expectToEqual(usp->URLSearchParams.get("1"), None);

expectToEqual(usp->URLSearchParams.entries, [|("2", "second")|]);

usp->URLSearchParams.append("2", "22");
expectToEqual(
  usp->URLSearchParams.entries,
  [|("2", "second"), ("2", "22")|],
);
expectToEqual(usp->URLSearchParams.getAll("2"), [|"second", "22"|]);
expectToEqual(usp->URLSearchParams.getAll("3"), [||]);

usp->URLSearchParams.set("2", "Second");
expectToEqual(usp->URLSearchParams.getAll("2"), [|"Second"|]);

// HEADERS

module Headers = Fetch.Headers;

let headers = Headers.makeWithObject({"h1": "v1", "h2": "v2", "h3": "v3"});
headers->Headers.append("h1", "v11");

expectToEqual(headers->Headers.values, [|"v1, v11", "v2", "v3"|]);
expectToEqual(headers->Headers.keys, [|"h1", "h2", "h3"|]);
expectToEqual(headers->Headers.get("h1"), Some("v1, v11"));
expectToEqual(headers->Headers.get("h5"), None);

expectToEqual(headers->Headers.has("h1"), true);
expectToEqual(headers->Headers.has("h5"), false);

headers->Headers.set("h1", "v111");
headers->Headers.delete("h2");
expectToEqual(headers->Headers.entries, [|("h1", "v111"), ("h3", "v3")|]);
headers->Headers.append("h2", "v2");
expectToEqual(
  headers->Headers.entries,
  [|("h1", "v111"), ("h2", "v2"), ("h3", "v3")|],
);

headers->Headers.delete("h1");
headers->Headers.delete("h3");

headers->Headers.forEach(x => expectToEqual(x, "v2"));

// XML HTTP REQUEST

let parts = [||];
for (_ in 1 to 100) {
  parts |> Js.Array.push(`String("hello ")) |> ignore;
};
let blob1 = Blob.make(parts, ());

open XmlHttpRequest;

let xhr = XmlHttpRequest.make();
xhr->setResponseType(`text);
xhr->onprogress(e => {
  Js.log("progress");
  Js.log2(e->loaded, e->total);
  expectToEqual(e->loaded->Js.typeof, "number");
  expectToEqual(e->total->Js.typeof, "number");
});
xhr->onload(e => {
  Js.log("load");
  Js.log2(e->loaded, e->total);
  expectToEqual(e->loaded->Js.typeof, "number");
  expectToEqual(e->total->Js.typeof, "number");

  expectToEqual(xhr->responseText, Some("hello world"));

  switch (xhr->response) {
  | Some(`String(str)) => expectToEqual(str, "hello world")
  | _ => failwith("fail")
  };
});
xhr->open_(`Get, "/1.txt", ());
xhr->sendBody(BodyInit.makeWithBlob(blob1));

let xhr = XmlHttpRequest.make();
xhr->setResponseType(`json);
xhr->onload(_ =>
  switch (xhr->response) {
  | Some(`Json(json)) =>
    expectToEqual(
      json
      ->Js.Json.decodeArray
      ->Option.getExn
      ->Array.getExn(0)
      ->Js.Json.decodeString
      ->Option.getExn,
      "john",
    )
  | _ => failwith("fail")
  }
);
xhr->open_(`Get, "/names.json", ());
xhr->send;

let xhr = XmlHttpRequest.make();
xhr->setResponseType(`json);
xhr->onload(_ =>
  switch (xhr->response) {
  | Some(`String(s)) => expectToEqual(s, "hello")
  | _ => failwith("fail")
  }
);
xhr->open_(`Get, "/1.json", ());
xhr->send;

let xhr = XmlHttpRequest.make();
xhr->setResponseType(`json);
xhr->onload(_ =>
  switch (xhr->response) {
  | Some(`Json(json)) =>
    expectToEqual(json->Js.Json.decodeNumber->Option.getExn, 321.0)
  | _ => failwith("fail")
  }
);
xhr->open_(`Get, "/2.json", ());
xhr->send;

let xhr = XmlHttpRequest.make();
expectToEqual(xhr->readyState, `UNSENT);
xhr->setResponseType(`blob);
xhr->onload(_ => {
  switch (xhr->response) {
  | Some(`Blob(b)) =>
    b->FileReader.toText()
    |> then_(s => {
         expectToEqual(s, "ReasonML");
         resolve();
       })
    |> ignore
  | _ => failwith("fail")
  };

  expectToEqual(xhr->readyState, `DONE);
});
xhr->open_(`Get, "/2.txt", ());
expectToEqual(xhr->readyState, `OPENED);

xhr->onreadystatechange(() => {
  Js.log2("state change", xhr->readyState);

  switch (xhr->readyState) {
  | `UNSENT => Js.log("--- UNSENT")
  | `OPENED => Js.log("--- OPENED")
  | `HEADERS_RECEIVED => Js.log("--- HEADERS_RECEIVED")
  | `LOADING => Js.log("--- LOADING")
  | `DONE => Js.log("--- DONE")
  };
});
xhr->send;
expectToEqual(xhr->readyState, `OPENED);

let xhr = XmlHttpRequest.make();
xhr->onload(_ => failwith("unreachable"));
xhr->onerror(_ => Js.log("expected error"));
xhr->open_(`Get, "file://unknown", ());
xhr->send;

let xhr = XmlHttpRequest.make();
xhr->onabort(_ => Js.log("expected abort"));
xhr->onload(_ => failwith("fail"));
xhr->open_(`Get, "/2.json", ());
xhr->send;
xhr->abort;

let findHi: Dom.document => string = [%raw
  {|
function(doc) {
  let s = doc.querySelector("span#hi");
  return s.textContent;
}
|}
];

let xhr = XmlHttpRequest.make();
xhr->setResponseType(`document);
xhr->onload(_ =>
  switch (xhr->response) {
  | Some(`Document(doc)) =>
    let hi = doc->findHi;
    expectToBe(hi, "Hello there");
  | _ => failwith("fail")
  }
);
xhr->open_(`Get, "/1.html", ());
xhr->send;

let doc: unit => Dom.document = [%bs.raw
  {|
function (unit) {
  var parser = new DOMParser();
  return parser.parseFromString("<test>hello</test>", "text/xml");
}
|}
];
let doc = doc();

/* send doc */
let xhr = XmlHttpRequest.make();
expectToEqual(xhr->responseType, `text);
xhr->open_(`Post, "/", ());
/* xhr->overrideMimeType("text/json"); */
xhr->sendDocument(doc);

let xhr = XmlHttpRequest.make();
xhr->setResponseType(`arraybuffer);
xhr->onload(_ => {
  switch (xhr->response) {
  | Some(`ArrayBuffer(ab)) =>
    let arr = ab->Js.Typed_array.Int8Array.fromBuffer;
    expectToEqual(arr->Js.Typed_array.Int8Array.length, 4);
    expectToBe(arr->Js.Typed_array.Int8Array.unsafe_get(0), 65);
  | _ => failwith("fail")
  };

  expectToEqual(xhr->getResponseHeader("content-length"), Some("4"));
  Js.log(xhr->getAllResponseHeaders);
  expectToEqual(
    xhr->getAllResponseHeaders->Option.getExn->Js.String.toLowerCase
    |> Js.String.includes("content-type"),
    true,
  );
});
xhr->open_(`Post, "/a.txt", ());
xhr->sendBody(BodyInit.make(""));

let xhr = XmlHttpRequest.make();

expectToEqual(xhr->statusText, "");
expectToEqual(xhr->responseURL, "");

xhr->setResponseType(`document);
xhr->onload(_ => {
  expectToEqual(xhr->responseXML->Option.isSome, true);
  Js.log(xhr->responseXML);

  expectToEqual(xhr->responseURL->Js.typeof, "string");
  expectToEqual(xhr->status, 200);
  expectToEqual(xhr->statusText, "OK");
});
xhr->open_(`Get, "/1.xml", ());
xhr->send;

let xhr = XmlHttpRequest.make();
xhr->setTimeout(1.0);
xhr->ontimeout(() => Js.log("timeout"));
xhr->onload(_ => ());
xhr->open_(`Get, "http:/aaaaaaaaazzzzzz.com", ());
xhr->send;

let xhr = XmlHttpRequest.make();
xhr->open_(
  `Get,
  "/?withuserpass",
  ~async=false,
  ~user="john",
  ~password="123",
  (),
);
xhr->send;

let usp = URLSearchParams.makeWithObject({"q": "werty", "a": "sdfg"});

let xhr = XmlHttpRequest.make();
xhr->open_(`Post, "/?usp", ());
xhr->sendBody(BodyInit.makeWithUrlSearchParams(usp));

let fd = FormData.make();
fd->FormData.append("1", `String("one"));
fd->FormData.append("2", `Blob(Blob.make([|`String("one")|], ())));

let xhr = XmlHttpRequest.make();
xhr->open_(`Post, "/?fd", ());
xhr->setRequestHeader("myheader", "sss");
xhr->sendBody(BodyInit.makeWithFormData(fd));

let file = Blob.make([|`String("content")|], ());
let body = BodyInit.makeWithBlob(file);
let headers = HeadersInit.makeWithObject({"1": "2"});

// name clash test
let fetch = 1;

fetchWithInit(
  "/?fetch-send-file",
  RequestInit.make(~method_=`Post, ~body, ~headers, ()),
);

fetchWithRequest(Request.make("/?fetch-req"));

let res =
  Response.make(
    ~body=BodyInit.make("qwerty"),
    ~init=ResponseInit.make(~status=322, ()),
    (),
  );
expectToEqual(res->Response.status, 322);

let r1 = Response.redirect("/");
expectToEqual(r1->Response.url, "");

Fetch.fetch("1.txt")
|> then_(Response.text)
|> then_(text => {
     expectToEqual(text, "hello world");
     resolve();
   });

let ac = Fetch.AbortController.make();
let signal = ac->Fetch.AbortController.signal;
signal->Fetch.AbortSignal.setOnAbort(() => {
  Js.log("ABORT EVENT");
});
let init = Fetch.RequestInit.make(~signal, ());

expectToEqual(signal->Fetch.AbortSignal.aborted, false);

Fetch.fetchWithInit("abort.txt", init)
|> then_(Response.text)
|> then_(text => {
  Js.log2("abort.txt", text);
  resolve();
});

ac->Fetch.AbortController.abort;
expectToEqual(signal->Fetch.AbortSignal.aborted, true);

Js.log("OK");
// [%raw {|
// (alert("OK"))
// |}];
