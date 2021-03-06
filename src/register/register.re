open HttpRequestModule;

let register = (email, password, firstName, lastName) => {};

type action =
  | UpdateEmail(string)
  | UpdatePassword(string)
  | UpdateFirstName(string)
  | UpdateLastName(string)
  | GoToLogin
  | Register;

type state = {
  email: string,
  password: string,
  firstName: string,
  lastName: string,
};

let component = ReasonReact.reducerComponent("Register");

let make = _children => {
  ...component,
  initialState: () => {email: "", password: "", firstName: "", lastName: ""},
  reducer: (action, state) => {
    switch (action) {
    | UpdateEmail(email) => ReasonReact.Update({...state, email})
    | UpdatePassword(password) => ReasonReact.Update({...state, password})
    | UpdateFirstName(firstName) => ReasonReact.Update({...state, firstName})
    | UpdateLastName(lastName) => ReasonReact.Update({...state, lastName})
    | GoToLogin =>
      ReasonReact.Router.push("login");
      ReasonReact.NoUpdate;
    | Register =>
      ReasonReact.SideEffects(
        _self =>
          doPost(
            "https://qsi-tochevoronwe.cleverapps.io/api/v1/users",
            Json.Encode.(
              object_([
                ("email", string(state.email)),
                ("password", string(state.password)),
                ("firstName", string(state.firstName)),
                ("lastName", string(state.lastName)),
              ])
            ),
            () =>
            ReasonReact.Router.push("score")
          ),
      )
    };
  },
  render: self => {
    <div>
      <h1> {ReasonReact.string("Register")} </h1>
      <div>
        {ReasonReact.string("email : ")}
        <input name="email" onChange={_evt => self.send(UpdateEmail(ReactEvent.Form.target(_evt)##value))} />
      </div>
      <div>
        {ReasonReact.string("password : ")}
        <input name="password" onChange={_evt => self.send(UpdatePassword(ReactEvent.Form.target(_evt)##value))} />
      </div>
      <div>
        {ReasonReact.string("First name : ")}
        <input
          name="firstname"
          onChange={_evt => self.send(UpdateFirstName(ReactEvent.Form.target(_evt)##value))}
        />
      </div>
      <div>
        {ReasonReact.string("Last name : ")}
        <input name="lastName" onChange={_evt => self.send(UpdateLastName(ReactEvent.Form.target(_evt)##value))} />
      </div>
      <button onClick={_ => self.send(Register)}> {ReasonReact.string("Register")} </button>
      <br />
      {ReasonReact.string("Already have an account ?")}
      <button onClick={_ => self.send(GoToLogin)}> {ReasonReact.string("Login")} </button>
    </div>;
  },
};
