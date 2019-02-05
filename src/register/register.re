let login = (email, password) => {};

type action =
  | Login;

type state = {
  email: string,
  password: string,
};

let component = ReasonReact.reducerComponent("Register");

let make = _children => {
  ...component,
  initialState: () => {email: "", password: ""},
  reducer: (action, state) => {
    switch (action) {
    | Login => ReasonReact.Update({email: state.email, password: state.password})
    };
  },
  render: self => {
    <div>
      <h1> {ReasonReact.string("Register")} </h1>
      <div> {ReasonReact.string("email : ")} <input name="email" /> </div>
      <div> {ReasonReact.string("password : ")} <input name="password" /> </div>
    </div>;
  },
};
