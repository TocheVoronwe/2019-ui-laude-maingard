[@bs.val] external alert : string => unit = "alert";

let doPost = (url: string, body, callBack) => {
    let promise = Js.Promise.(
        Fetch.fetchWithInit(
        url,
        Fetch.RequestInit.make(
                ~method_=Post,
                ~body=Fetch.BodyInit.make(Js.Json.stringify(body)),
                ~headers=Fetch.HeadersInit.make({"mode": "cors", "Content-Type": "application/json", "Access-Control-Allow-Origin": "*"}),
                ()
                )
        )
        |> then_(Fetch.Response.json)
        |> then_(value => {
            Json.Decode.{
                "success": value |> field("success", bool),
                "message": value |> field("message", string)
            }
            |> (response => {
                switch response##success {
                    | false => {
                        alert(response##message)
                        Js.Promise.resolve(response)
                    }
                    | _ => {
                        callBack();
                        Js.Promise.resolve(response)
                    }
                };
            })
        })
    );
}