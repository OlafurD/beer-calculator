open Css;

let component = ReasonReact.statelessComponent("Input");

/* let formatFloat = (value) => {
  let valueString = string_of_float(value);
  let length = String.length(valueString); 
  if((valueString |. String.index('.')) == length - 1) {
    Js.log("IN THINGY");
    valueString |. String.sub(0, length - 1);
  } else {
    Js.log("OTHER THINGY");
    valueString
  }
  
};

let backToFloat = (value) => {
  let indx = try(value |. String.index('.')) {
  | exn => -1
  };

  if(indx == - 1) {
    Js.log("WHATUP");
    value ++ "."
  } else {
    Js.log("WHATUP2");
    value
  }
}; */
  

let make = (~fieldName, ~value, ~action, ~callback, _children) => {
  ...component,
  render: self =>
    <div>
      <span> (ReasonReact.string(fieldName)) </span>
      <input
        _type="text"
        name="grain-weight"
        value=(
                if(value == 0) "" else string_of_int(value)
              )
        onChange=(
          ev =>
            callback(
              action(ReactDOMRe.domElementToObj(ReactEventRe.Form.target(ev))##value)
            )
        )
      />
    </div>,
};