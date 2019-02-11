let login = (email, password) => {};

type action =
  | Login;

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
    | Login => ReasonReact.Update({email: state.email, password: state.password})
    };
  },
  render: self => {
    <div>
      <h1> {ReasonReact.string("Péniche")} </h1>
      <div> {ReasonReact.string("péniche : ")} <input name="email" /> </div>
      <div> {ReasonReact.string("péniche : ")} <input name="password" /> </div>
    </div>;
  },
};
