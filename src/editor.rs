use iced::{Column, Element, Text};

#[derive(Debug)]
pub struct Editor {
	pub editor_type: EditorType,
	pub maximised: bool,
}

impl Editor {
	fn new() -> Editor {
		Editor {
			editor_type: EditorType::Settings,
			maximised: false,
		}
	}

	fn update(&mut self, _msg: StepMessage, _debug: &mut bool) {
		// self.editor_type[self.current].update(msg, debug);
	}

	fn view(&mut self, debug: bool) -> Element<StepMessage> {
		self.editor_type.view(debug)
	}
}

#[derive(Debug)]
pub enum EditorType {
	Settings,
	Nodes,
}

#[derive(Debug, Clone)]
pub enum StepMessage {
	MaximisedToggled(bool),
	DebugToggled(bool),
}

impl EditorType {
	fn update(&mut self, msg: StepMessage, debug: &mut bool) {
		match msg {
			StepMessage::DebugToggled(new_value) => {}
			StepMessage::MaximisedToggled(new_value) => {}
		};
	}

	fn title(&self) -> &str {
		match self {
			EditorType::Settings => "Settings Editor",
			EditorType::Nodes => "Nodes Editor",
		}
	}

	fn view(&mut self, _debug: bool) -> Element<StepMessage> {
		match self {
			EditorType::Settings => Self::container("Settings Editor"),
			EditorType::Nodes => Self::container("Nodes Editor"),
		}
		.into()
	}

	fn container(title: &str) -> Column<StepMessage> {
		Column::new().spacing(20).push(Text::new(title).size(50))
	}
}
