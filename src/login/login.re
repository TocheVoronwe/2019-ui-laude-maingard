let login = (email, password) => {};

type action =
  | UpdateEmail(string)
  | UpdatePassword(string)
  | GoToRegister
  | GoToScore
  | Submit;

type state = {
  email: string,
  password: string,
};

let component = ReasonReact.reducerComponent("Login");

let make = _children => {
  ...component,
  initialState: () => {email: "", password: ""},
  reducer: (action, state) => {
    switch (action) {
    | UpdateEmail(email) => ReasonReact.Update({...state, email})
    | UpdatePassword(password) => ReasonReact.Update({...state, password})
    | GoToRegister =>
      ReasonReact.Router.push("register");
      ReasonReact.NoUpdate;
    | GoToScore =>
      ReasonReact.Router.push("score");
      ReasonReact.NoUpdate;
    | Submit =>
      ReasonReact.SideEffects(
        _self => {
          Js.Promise.(
            Fetch.fetchWithInit(
              "https://qsi-tochevoronwe.cleverapps.io/api/v1/users/login",
              Fetch.RequestInit.make(
                ~method_=Post,
                ~body=
                  Fetch.BodyInit.make(
                    Js.Json.stringify(
                      Json.Encode.(
                        object_([("email", string(state.email)), ("password", string(state.password))])
                      ),
                    ),
                  ),
                ~headers=
                  Fetch.HeadersInit.make({
                    "mode": "cors",
                    "Content-Type": "application/json",
                    "Access-Control-Allow-Origin": "*",
                  }),
                (),
              ),
            )
            |> then_(value => {
                 Js.log(value);
                 Js.Promise.resolve(value);
               })
          );
          ();
        },
      )
    };
  },
  render: self => {
    <div>
      <h1> {ReasonReact.string("Login")} </h1>
      <div>
        {ReasonReact.string("email : ")}
        <input name="email" onChange={_evt => self.send(UpdateEmail(ReactEvent.Form.target(_evt)##value))} />
      </div>
      <div>
        {ReasonReact.string("password : ")}
        <input name="password" onChange={_evt => self.send(UpdatePassword(ReactEvent.Form.target(_evt)##value))} />
      </div>
      <button onClick={_ => self.send(GoToRegister)}> {ReasonReact.string("Register")} </button>
      <button onClick={_ => self.send(Submit)}> {ReasonReact.string("Login")} </button>
    </div>;
  },
};
