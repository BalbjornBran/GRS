# 🎮 Gameplay Reaction System

A modular, event-driven Reaction System built on top of Unreal Engine's Gameplay Ability System (GAS).

Designed to allow developers and designers to define reactions to attribute changes (like health or stamina), without writing custom logic in every character or pawn. Reactions can apply/remove gameplay effects, trigger cues, send events, or execute custom logic — all configurable via DataAssets.

### Feature Design Proposal:  
[View on Notion](https://www.notion.so/Gameplay-Reaction-System-Feature-Design-Proposal-1da2cb6e5e86807eb1defb72d0e0f902?pvs=4)

---

## ⚙️ Core Features

- 🔁 Fully event-driven (no polling or tick required).
- ⚡ Modular and expandable with `UGameplayReaction` subclasses.
- 📦 Configurable via `DataAssets` for design-friendly setup.
- 📉 React to attribute changes (e.g., health reaching 0).
- 📈 Filter reactions by threshold and direction (increase/decrease).
- 💀 Includes default reactions like: apply or remove Gameplay Effects, Trigger GameplayEvents, Trigger GameplayCues
- 🎯 Compatible with GAS in PlayerState, Controller or Pawn setups.

---

## 🧱 How It Works

1. Add `UGameplayReactionAttributeComponent` to any actor with an `AbilitySystemComponent`.
2. Assign a `GameplayReactionsDataAsset` with the list of attributes to observe.
3. For each attribute, assign one or more `UGameplayReaction` objects.
4. Reactions will trigger automatically based on value changes and conditions.

---

## 🧩 Built-in Reactions

- `GR_HandleGameplayEffect`: Apply or remove GameplayEffects.
- `GR_TriggerGameplayCue`: Play visual/audio effects via Cue.
- `GR_SendGameplayEvent`: Send GameplayEvents to ASC.
- `GR_SimpleLog`: Debug-friendly log reaction.

---

## 📝 Example Use Case

- Health reaches 0 → `GameplayReaction_HandleDeath` triggers.
- Optionally sends a `GameplayEvent` like `Event.Death`.

---

## ✅ Requirements

- Unreal Engine 5.3+ (tested with GAS integration).
- `AbilitySystemComponent` present on the Actor.

---

## 📌 Notes

- Designed to be easily extended with new `UGameplayReaction` types.
- Clean separation of logic for design scalability.
- Ideal for GAS-heavy gameplay systems.
- Still in WIP state

---


