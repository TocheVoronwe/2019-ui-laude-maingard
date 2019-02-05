type email = string;
type password = string;

type state = {
  email,
  password,
};

let component = ReasonReact.reducerComponent("Register");

let make = _children => {
  ...component,
  reducer: state => {
    ReasonReact.Update({email: state.email});
  },
  render: self => {
    <div>
      <h1> {ReasonReact.string("Register")} </h1>
      <div> {ReasonReact.string("email : ")} <input name="email" /> </div>
      <div> {ReasonReact.string("password : ")} <input name="password" /> </div>
    </div>;
  },
};
