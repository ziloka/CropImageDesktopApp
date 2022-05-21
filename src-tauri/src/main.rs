#![cfg_attr(
  all(not(debug_assertions), target_os = "windows"),
  windows_subsystem = "windows"
)]

use tauri::{CustomMenuItem, Menu, MenuItem, Submenu};
use tauri::api::dialog::FileDialogBuilder;

#[derive(Clone, serde::Serialize)]
struct Payload {
  folder_name: std::path::PathBuf
}

fn main() {
  let quit = CustomMenuItem::new("quit".to_string(), "Quit");
  let open = CustomMenuItem::new("open".to_string(), "Open");
  let submenu = Submenu::new("File", Menu::new().add_item(open).add_item(quit));
  let menu = Menu::new()
    .add_native_item(MenuItem::Copy)
    .add_submenu(submenu);
  tauri::Builder::default()
    .menu(menu)
    .on_menu_event(|event| {
        match event.menu_item_id() {
          "quit" => {
            std::process::exit(0);
          }
          "open" => {
            FileDialogBuilder::new().pick_folder(move |file_path| {
              match file_path {
                Some(ref x) => {
                  event.window().emit("folderChanged", Payload { folder_name: x.to_path_buf() }).unwrap();
                },
                None => println!("Open menu: User did not select a directory")
              }
            })
          }
          _ => {}
        }
    })
    .run(tauri::generate_context!())
    .expect("error while running tauri application");
}
